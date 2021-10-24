from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from controlPanel import *

import json

class Main(QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.save_setting()
    
    def save_setting(self):
        self.ui.apply_button.clicked.connect(self.write_json)

    def write_json(self):
        with open('time_setting.json', 'w') as f:
            json.dump(
                {
                    "led" : {
                        "on" : self.write_dict(self.ui.led_time_on.text()),
                        "off" : self.write_dict(self.ui.led_time_off.text())
                    },
                    "water" : {
                        "on" : self.write_dict(self.ui.water_time_on.text()),
                        "off" : self.write_dict(self.ui.water_time_off.text())
                    }
                }, f)

    def write_dict(self, time):        
        if time[-2:] == "PM":
            if time[1] == ":":
                time = str(int(time[0:1]) + 12) + time[1:]
            else:
                if time[0:2] != "12":
                    time = str(int(time[0:2]) + 12) + time[2:]

            time_dict = {"hour" : time[0:2], "min" : time[3:5]}
        else:
            if time[1] == ":":
                time_dict = {"hour" : time[0:1], "min" : time[2:4]}
            else:
                if time[0:2] == "12":
                    time = str(int(time[0:2]) + 12) + time[2:]
                time_dict = {"hour" : time[0:2], "min" : time[3:5]}
   
        return time_dict

if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    main = Main()
    main.show()
    sys.exit(app.exec_())