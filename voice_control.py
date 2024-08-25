from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.label import Label
import speech_recognition as sr
import bluetooth

# Bluetooth setup
bt_addr = "00:00:00:00:00:00"  # Replace with your Bluetooth module address
bt_port = 1
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((bt_addr, bt_port))

class VoiceControlApp(App):
    def build(self):
        layout = BoxLayout(orientation='vertical')
        self.label = Label(text='Say a command...')
        layout.add_widget(self.label)
        btn = Button(text='Start Listening')
        btn.bind(on_press=self.start_listening)
        layout.add_widget(btn)
        return layout

    def start_listening(self, instance):
        recognizer = sr.Recognizer()
        with sr.Microphone() as source:
            self.label.text = 'Listening...'
            audio = recognizer.listen(source)
            try:
                command = recognizer.recognize_google(audio).lower()
                self.label.text = f'Command: {command}'
                # Send command to Arduino
                sock.send(command)
            except sr.UnknownValueError:
                self.label.text = 'Could not understand audio'
            except sr.RequestError:
                self.label.text = 'Could not request results'

if __name__ == '__main__':
    VoiceControlApp().run()
