# DriverLoading

> 开发环境：win11 测试：win10 ltsc

### 如何使用

**管理员身份运行**

```shell
# 安装驱动1 DriverPath DriverName
C:\Users\ab\Desktop>DriverLoading.exe 1 C:\Users\ab\Desktop\DriverTest.sys DriverTest
[DriverLoading] Successful

# 执行驱动2 DriverName
C:\Users\ab\Desktop>DriverLoading.exe 2 DriverTest
[DriverActivate] Successful

# 停止驱动3 DriverName
C:\Users\ab\Desktop>DriverLoading.exe 3 DriverTest
[DriverClose] Successful

# 卸载驱动4 DriverName
C:\Users\ab\Desktop>DriverLoading.exe 4 DriverTest
[DriverUnload] Successful
```

使用procexp查看加载结果

### Debug打印

00002015	78.19476318	[DriverTest] DriverEntry	
00002230	190.52050781	[DriverTest] DriverUnload	