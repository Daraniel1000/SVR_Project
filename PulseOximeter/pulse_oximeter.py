import math
import sys
import threading
import time

from http.server import BaseHTTPRequestHandler, HTTPServer

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import *


MIN_PULSE = 70
MAX_PULSE = 170
FREQUENCY = 0.04
SERVER_NAME = "localhost"
SERVER_PORT = 8080


pulse = MIN_PULSE


class GUI(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Pulse oximeter")
        self.setGeometry(0, 0, 250, 150)

        widget = QWidget()
        widget.setLayout(self.__prepare_main_layout())

        self.setCentralWidget(widget)

    def __prepare_main_layout(self):
        layout = QGridLayout()
        layout.setSpacing(20)

        self.check = QCheckBox("Auto (sinusoid)")
        self.check.clicked.connect(self.use_sinusoid)
        layout.addWidget(self.check, 0, 0, 1, 2)

        self.slider = QSlider(Qt.Orientation.Horizontal, self)
        self.slider.setFixedWidth(120)
        self.slider.setMinimum(MIN_PULSE)
        self.slider.setMaximum(MAX_PULSE)
        self.slider.valueChanged.connect(self.changed_value)
        layout.addWidget(self.slider, 1, 0)

        self.label = QLabel(str(self.slider.value()))
        layout.addWidget(self.label, 1, 1)

        spacer = QWidget()
        layout.addWidget(spacer)

        return layout

    def use_sinusoid(self, value):
        self.slider.setDisabled(value)
        if value:
            threading.Thread(target=self.sinusoid).start()

    def changed_value(self, value):
        self.label.setText(str(value))
        global pulse
        pulse = value

    def sinusoid(self):
        while True:
            factor = (MAX_PULSE - MIN_PULSE) / 2
            value = int(factor * math.sin(FREQUENCY * time.time()) + factor + MIN_PULSE)

            self.slider.setValue(value)
            self.label.setText(str(value))

            global pulse
            pulse = value

            time.sleep(0.05)

            if not self.check.isChecked():
                break


class Server(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        self.wfile.write(bytes(str(pulse), "utf8"))


def start_server():
    web_server = HTTPServer((SERVER_NAME, SERVER_PORT), Server)
    print("Server started.")

    try:
        web_server.serve_forever()
    except KeyboardInterrupt:
        pass

    web_server.server_close()
    print("Server stopped.")


if __name__ == "__main__":
    threading.Thread(target=start_server).start()

    app = QApplication(sys.argv)

    window = GUI()
    window.show()

    app.exec()
