# 📦 Inventory Management System (C++)

A console-based Inventory Management System developed in **C++**, using **file handling** for persistent data storage.
The project simulates a real-world inventory and billing workflow with role-based access for administrators and employees.

---

## 🚀 Features

### 🔐 Role-Based Access

* **Admin**

  * Manage inventory records
  * View and manage employee data
  * Access invoices and sales records
* **Employee**

  * Generate bills
  * Update product quantities
  * Handle sales and returns

---

### 📦 Inventory Management

* Add, update, and remove stock items
* Check real-time stock availability
* Prevent invalid or insufficient stock operations
* Persistent inventory storage using files

---

### 📄 Billing & Invoicing

* Automatic invoice number generation
* GST calculation
* Bill generation and printing
* Refund and return handling
* View bills using invoice number
* Retrieve bills within a date range

---

### 📁 File-Based Persistence

* Uses `fstream` to store:

  * Inventory data
  * Bills and invoices
  * Temporary transaction data
* Ensures data consistency using temporary files and safe overwrite logic

---

### 📅 Date Handling

* Manual date validation
* Leap year handling
* Month-wise day validation
* Date-range based report generation

---

### 📸 Screenshots

### Admin Dashboard

<img width="692" height="271" alt="image" src="https://github.com/user-attachments/assets/cedf8927-276f-453b-ba93-7a6c582fb1e2" />

### Show Inventory Screen

<img width="1087" height="196" alt="image" src="https://github.com/user-attachments/assets/71a0a0bf-eaa5-4da5-a0e3-d83858c029e1" />

### Bill Generation

<img width="1029" height="193" alt="image" src="https://github.com/user-attachments/assets/08c3a23b-d6f5-4b45-9e17-b2c7986f3c02" />

### Refund Processing

<img width="580" height="118" alt="image" src="https://github.com/user-attachments/assets/1377f228-57ae-4845-bdcc-9a0dcb1e00c4" />

---

## 🛠️ Technologies Used

* **Language:** C++
* **Concepts:**

  * File Handling (`fstream`)
  * Object-Oriented Programming
  * Control Flow & Validation
  * Business Logic Implementation
* **Data Storage:** Text files (no database)

---

## 📂 Project Structure

```
inventory-management-system-cpp/
│
├── inventory_management_system.cpp
├── README.md
└── data files (generated at runtime)
```

> Note: Data files are created automatically when the program runs.

---

## ▶️ How to Run

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/inventory-management-system-cpp.git
   ```

2. Compile the program:

   ```bash
   g++ inventory_management_system.cpp -o ims
   ```

3. Run:

   ```bash
   ./ims
   ```
