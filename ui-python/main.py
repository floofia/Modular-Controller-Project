# Import required libraries
import serial.tools.list_ports
from serial import *
from tkinter import *
import tkinter.ttk as ttk
from PIL import ImageTk, Image


#serialPort = "/dev/ttyACM0"
#baudRate = 9600
#ser = Serial(serialPort , baudRate, timeout=0, writeTimeout=0) #ensure non-blocking

# --- functions ---

    

def serial_ports():    
    return serial.tools.list_ports.comports()

def module_write():
    return 5


def on_select(event=None):

    # get selection from event    
    print("event.widget:", event.widget.get())

    # or get selection directly from combobox
    print("comboboxes: ", cb.get())

#--- main ---

# Create an instance of tkinter window
win = Tk()
win.wm_title("Really Cool Window")

#custom icon
icon = PhotoImage(file = 'me.PNG')
win.wm_iconphoto(False, icon)



cb = ttk.Combobox(win, values=serial_ports())
cb.pack()

# assign function to combobox
cb.bind('<<ComboboxSelected>>', on_select)


#create a scrollbar
scrollbar = Scrollbar(win)
scrollbar.pack(side=RIGHT, fill=Y)

# Create an object of tkinter ImageTk
img = ImageTk.PhotoImage(Image.open("me.PNG"))

# make a text box to put the serial output
log = Text ( win, width=30, height=30, takefocus=0)
log.pack(side=LEFT, fill=Y)

# Define the geometry of the window
win.geometry("1000x800")

frame = Frame(win, width=600, height=400)
frame.pack(side=RIGHT)
frame.place(anchor='center', relx=0.5, rely=0.5)

#add button
button1 = Button(text='Get the Square Root')
button1.pack(side=BOTTOM)



# Create a Label Widget to display the text or Image
label = Label(frame, image = img)
label.pack()

win.mainloop()