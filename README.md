# Polar ImGui
This is an implementation of ImGui for Android Unity-based games using il2cpp.

**[Visit the Polarmods forum](https://polarmods.com/)**

**[Join our Discord](https://discord.gg/swFjrMZuYr)**

## Android Studio
1. First of all, download Android Studio [here](https://developer.android.com/studio). Then, complete the installation process.
2. Download the PolarImGui repository, and extract it with any archiver (such as 7-Zip, WinRAR, etc).
 
![image](https://user-images.githubusercontent.com/64957743/173016188-401c7a8f-7fce-4f7a-b560-453098e8b0e0.png)

![image](https://user-images.githubusercontent.com/64957743/173016572-d18c5ba9-00ff-43d1-9f0c-9c163d3e255d.png)

3. Now, open the project in Android Studio. You will need to wait for the gradle to sync once it is open. As for the NDK, I recommend using the latest lts version, which can be downloaded [here](https://dl.google.com/android/repository/android-ndk-r23c-windows.zip).

![image](https://user-images.githubusercontent.com/64957743/173019991-0d7db98d-6b67-41e0-a0a0-c34f5a68fe78.png)

4. Build it! (Build -> Build Bundle(s)/APK(s) -> Build APK(s), or Ctrl + F9).

## Implementation
Implementing the menu into an application is very easy, just follow the steps below!

1. Once you build the apk, open it using an archiver (such as 7-Zip, WinRAR, etc), and find the 'lib' directory.

![image](https://user-images.githubusercontent.com/64957743/173011691-9563f44f-840a-400e-9931-7a80eb816ea7.png)

From there, you will be presented with two additional folders. Choose the folder that resembles the cpu architecture you want to use (whether it be armeabi-v7a, or arm64-v8a). I would also like to mention that you can implement both libraries into a game if it supports ARMv7a and ARMv8a, and it will work for most games (Guns of Boom did crash when I tested this on that game though)! So, there is no need to remove the folders as you 'normally' would.

![image](https://user-images.githubusercontent.com/64957743/173011171-7a89375d-8477-4a90-93ce-6998100aca04.png)

2. Move the 'libnative-lib.so' library to the target applications lib/chosen-cpu-architecture/ folder.

![image](https://user-images.githubusercontent.com/64957743/173011227-a94a7889-4d23-4803-a796-652a34f6f3dc.png)

3. Then, find your applications launch activity, and place the following code under the 'onCreate' method in that launch activity.

```
const-string v0, "native-lib"
invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

![image](https://user-images.githubusercontent.com/64957743/173011463-7721f889-76e6-4df2-8bcd-b9fc04445262.png)

4. Compile it!

## Notes
* This was the first ImGui Android implementation for Unity-based games using il2cpp, before people (whom we won't mention) leeched from it to create their own version. Yes, we will be updating the menu with new features when we can.

<img width="1276" alt="POLARMODS-BANNER-HQ-2" src="https://user-images.githubusercontent.com/64957743/173014961-edc5c55f-8dca-4c39-a1aa-c3a22f8beb22.png">
