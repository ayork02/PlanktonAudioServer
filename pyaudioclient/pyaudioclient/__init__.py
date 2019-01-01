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
	def __del__(self):
		self.s.close()
	def play(self, filepath, pos = 0):
		output = filepath
		if pos != 0:
			output += "||" + str(pos)
		output += "\n"
		self.s.send(output.encode())
	def stop(self):
		output = "stop\n"
		self.s.send(output.encode())
	def timecode(self):
		output = "time\n"
		self.s.send(output.encode())
		input = self.s.recv(20).decode()
		input = input[:-1]
		return float(input)