import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk
import os

def open_image():
    global img, photo, canvas, rectangle, current_zoom, save_button, img_x, img_y, image_path
    file_path = filedialog.askopenfilename(filetypes=[("BMP files", "*.bmp")])
    if file_path:
        img = Image.open(file_path)
        image_path = os.path.basename(file_path)
        current_zoom = 1.0
        img_x, img_y = 0, 0
        resize_and_display()
        save_button["state"] = tk.NORMAL

def resize_and_display():
    global img, photo, canvas, rectangle, current_zoom, img_x, img_y
    scaled_img = img.resize((int(img.width * current_zoom), int(img.height * current_zoom)), Image.LANCZOS)
    photo = ImageTk.PhotoImage(scaled_img)

    canvas_width = canvas.winfo_width()
    canvas_height = canvas.winfo_height()

    img_x = (canvas_width - scaled_img.width) / 2
    img_y = (canvas_height - scaled_img.height) / 2

    canvas.create_image(img_x, img_y, anchor=tk.NW, image=photo)

    if rectangle:
        canvas.delete(rectangle)

    create_rectangle(img_x, img_y)

def create_rectangle(x, y):
    global rectangle
    rectangle = canvas.create_rectangle(x, y, x + 64, y + 89, outline="red", width=2)
    canvas.tag_bind(rectangle, "<ButtonPress-1>", start_drag)
    canvas.tag_bind(rectangle, "<B1-Motion>", drag)

def start_drag(event):
    global prev_x, prev_y
    prev_x, prev_y = event.x, event.y

def drag(event):
    global prev_x, prev_y, img_x, img_y
    canvas.move(rectangle, event.x - prev_x, event.y - prev_y)
    prev_x, prev_y = event.x, event.y
    img_x += event.x - prev_x
    img_y += event.y - prev_y

def scale_image(event):
    global current_zoom
    scale_factor = 1.1 if event.delta > 0 else 0.9
    current_zoom *= scale_factor
    resize_and_display()

def save_data():
    global current_zoom, img_x, img_y, image_path
    x1, y1, w, h = canvas.coords(rectangle)
    w -= x1
    h -= y1
    x1 -= img_x
    y1 -= img_y
    x1 /= current_zoom
    w /= current_zoom
    y1 /= current_zoom
    h /= current_zoom
    

    with open(os.path.curdir + "/assets/cards/card_data.bruh", "a") as file:
        file.write("{\n")
        file.write(f"\tfile_name: {image_path}\n")
        file.write(f"\tcard_name: {image_path.removesuffix('.bmp')}\n")
        file.write(f"\tcutout_rect: {int(x1)} {int(y1)} {int(w)} {int(h)}\n")
        file.write("}\n")

if __name__ == "__main__":
    root = tk.Tk()
    root.title("Image cutter")

    canvas = tk.Canvas(root, width=800, height=600)
    canvas.pack()

    open_button = tk.Button(root, text="Open BMP", command=open_image)
    open_button.pack(pady=10)

    save_button = tk.Button(root, text="Save", command=save_data, state=tk.DISABLED)
    save_button.pack(pady=10)

    canvas.bind("<MouseWheel>", scale_image)

    prev_x, prev_y = 0, 0
    image_path = None
    img = None
    photo = None
    rectangle = None
    current_zoom = 1.0
    img_x, img_y = 0, 0

    root.mainloop()
