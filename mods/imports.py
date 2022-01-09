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
