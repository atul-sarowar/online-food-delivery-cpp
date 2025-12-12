# Online Food Delivery Order System (C++ | Data Structures Mini Project)

This is a terminal-based Online Food Delivery Order System developed using C++ and fundamental Data Structures as part of the CSE-207 (Data Structures) Mini Project under the supervision of Dr. Nafis Sadeq, Assistant Professor, Department of Computer Science & Engineering, East West University.

The project demonstrates real-world application of:
- Queue for managing incoming orders (FIFO)
- Min-Heap (Priority Queue) for driver availability
- Hash Map for tracking orders using Order ID

------------------------------------------------------------

Course Information

Course Title: Data Structures  
Course Code: CSE-207  
Instructor: Dr. Nafis Sadeq  
University: East West University  
Project Type: Mini Project (Terminal-Based System)

------------------------------------------------------------

Group Members

Saif Sarowar Atul    
Istiak Ahmed Siam  
Umme Kulsum        

------------------------------------------------------------

Features of the System

1. Place new food orders  
2. Assign next available delivery driver  
3. Track orders by Order ID  
4. Mark orders as delivered  
5. View all orders summary  
6. Automatic driver re-availability using Min-Heap  

------------------------------------------------------------

Data Structures Used

Queue    → Stores incoming customer orders  
Min-Heap → Stores drivers based on earliest availability  
Hash Map → Maps Order ID to order details for fast lookup  

------------------------------------------------------------

How to Run This Project on Any Computer

Step 1: Install a C++ Compiler

Make sure g++ is installed on your system.

Windows:
- Install MinGW-w64
- Add it to your system PATH

Linux:
Run the following command:
sudo apt install g++

Mac:
Run the following command:
brew install gcc
Note: If your system already has Code::Blocks with MinGW, you do not need to install g++ separately. Simply open the project and build it normally.
------------------------------------------------------------

How to Compile and Run the Project

Step 2: Open Terminal in Project Folder

After downloading or cloning the repository, open a terminal inside the project folder where all .cpp and .h files are located.

Windows:
- Hold Shift + Right Click inside the folder  
- Click "Open Command Prompt here" or "Open PowerShell here"

Linux / Mac:
- Right click inside the folder → Open in Terminal

------------------------------------------------------------

Step 3: Compile the Project (One Time Only)

Run this command to compile all source files into a single executable:

g++ -std=c++17 main.cpp order.cpp driver.cpp order_queue.cpp driver_min_heap.cpp order_hash_map.cpp food_delivery_system.cpp -o delivery_system

If there are no errors, the compilation is successful.  
A new file named delivery_system (or delivery_system.exe on Windows) will be created.

------------------------------------------------------------

Step 4: Run the Program

Windows:
delivery_system.exe

Linux / Mac:
./delivery_system

After running, the terminal menu of the Online Food Delivery Order System will appear.

------------------------------------------------------------

Step 5: Use the System

From the terminal menu you can:

- Place new food orders  
- Assign the next available driver  
- Track an order by Order ID  
- Mark orders as delivered  
- View all orders summary  

All operations are performed through the terminal interface.

------------------------------------------------------------


------------------------------------------------------------

  

------------------------------------------------------------

This project was created for academic purposes as part of the CSE-207 Data Structures Mini Project at East West University.
