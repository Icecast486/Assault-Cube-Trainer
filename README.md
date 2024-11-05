# Assault Cube Trainer x86
This is an internal trainer for AssaultCube 1.3.0.2. This project is a way for me to practice my reverse engeneering 
skills, using IDA PRO, cheat engine, re-class, and in addition keeping track of the changes I make 
to the project.

## DLL Injection Instructions

To use the internal trainer, follow these steps to inject the DLL into the target application:

1. **Download a DLL Injector**:
   - If you don’t already have one, download a trusted DLL injector (e.g., Extreme Injector or Xenos Injector).

2. **Open the DLL Injector**:
   - Run the DLL injector as an administrator to ensure you have the necessary permissions.

3. **Select the Target Process**:
   - Start the target application you want to inject into, in this case "ac_client.exe".
   - In the injector, choose this process from the list of active processes.

4. **Add the DLL**:
   - Select the option to add a DLL, and browse to the location of the internal trainer DLL (trainer.dll).

5. **Inject the DLL**:
   - Click "Inject" or a similar option, depending on the injector. This should inject the DLL into the target application.

6. **Confirm Injection**:
   - Check if the trainer interface (a console window). If it doesn’t, recheck the steps or try restarting the process.

## Usage

After injecting the DLL, use the following keys to control the trainer:

- **END**: Press to uninject the cheat and stop the trainer.
- **F1**: Activates Godmode.
- **F2**: Enables Infinite Ammo.
- **F3**: Toggles Aimbot.
