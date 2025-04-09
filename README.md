# BackupCleaner

**BackupCleaner** is a simple and efficient Windows desktop utility designed to automatically clean up old backup files from specified folders. It helps manage disk space by removing files based on:

- ✅ Maximum file **age** (in days)
- ✅ Total **folder size** limit (in MB)
- ✅ Maximum number of **files** in the folder

This is especially useful for automated backup systems, log folders, or temp storage that tends to grow over time.

---

## ✨ Features

- 🕒 Delete files older than `N` days
- 📁 Limit number of backup files to `Y` per folder
- 📂 Add multiple folders for monitoring
- 🔄 Automatically run daily via **BackupCleaner** task in Windows task scheduler.
- 🧾 Simple WinForms GUI for easy configuration

---

## 💻 UI Preview
![image](https://github.com/user-attachments/assets/3a1cc4ea-34d5-4ee8-827c-8f1b3e6f53d0)



---

## 🚀 Getting Started
- Push "New Folder" to choose folder you like to add.
- After getting path, press "Add" button and set all values you would like to track.
- "0" value means that this rule will not work. Value sets as soon as Text Box loose focus or you pressing Enter button.
- Scheduler starting task automaticaly every day at 00:00. If it skipped in some way, it will start on Windows start.
- "Delete Task" deleting only this folder processing.
- In case you moving folder to another location,but would like to keep the same rules for it, you always can change folder path in instance("Choose folder").
- Also program right now has protection, which wouldn't let deleting anything from C: disk.




