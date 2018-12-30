import socket
import errno
import time

class Client:
    def __init__(self, ip, port = 5005):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        for attempt in range(20):
			try:
				self.s.connect((ip, port))
			except EnvironmentError as exc:
				if exc.errno == errno.ECONNREFUSED:
					time.sleep(0.2)
			else:
				break
    def send_message(self, msg):
        output = msg + "\n"
        self.s.send(output.encode())

c = Client("10.0.0.18")
c.send_message("Hello World")
