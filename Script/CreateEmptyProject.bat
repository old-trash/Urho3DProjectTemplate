set "path=c:\Windows\Microsoft.NET\Framework\v4.0.30319\"
csc /target:exe /out:EmptyProject.exe EmptyProject.cs
EmptyProject.exe
del EmptyProject.exe
