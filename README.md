# Polar ImGui
[Visit Polarmods](https://polarmods.com/)
Better documentation will be provided once I (Rev) am back from school.

## Implementation
Implementing the menu into an application is very easy. All you need to do is find your applications launch activity, and place the following code under the 'onCreate' method in that launch activity.

```
const-string v0, "native-lib"
invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

## Notes
* This is the first ImGUI Android implementation for Unity, before people (whom we won't mention) leeched from it to create their own version of it.
