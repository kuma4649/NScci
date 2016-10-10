using System;
using System.Runtime.InteropServices;
using NScci;

namespace NScci
{
    public class SoundInterfaceManager
    {

        [DllImport("scci.dll", SetLastError = true, CharSet = CharSet.Unicode, ExactSpelling = true, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr getSoundInterfaceManager();

        [DllImport("kernel32.dll")]
        static extern IntPtr LoadLibrary(string lpFileName);
        [DllImport("kernel32.dll")]
        static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
        [DllImport("kernel32.dll")]
        static extern bool FreeLibrary(IntPtr hLibModule);

        delegate IntPtr getSoundInterfaceManagerDelegate();
        [return: MarshalAs(UnmanagedType.Bool)]
        delegate Boolean initializeInstanceDelegate();


        public void Init()
        {
            NScci cls = new NScci();

            int n=cls.getInterfaceCount();

            cls.Dispose();

            //// 関数ポインタを取得
            //IntPtr ptrLib = LoadLibrary("scci.dll");

            //try
            //{
            //    IntPtr ptrLoad = GetProcAddress(ptrLib, "getSoundInterfaceManager");
            //    // 関数ポインタをデリゲートに変換する 
            //    getSoundInterfaceManagerDelegate getSIM
            //        = (getSoundInterfaceManagerDelegate)Marshal.GetDelegateForFunctionPointer(ptrLoad, typeof(getSoundInterfaceManagerDelegate));
            //    IntPtr sim = getSIM();
            //    IntPtr ii = GetProcAddress(ptrLib, "SoundInterfaceManager::initializeInstance");// @SoundInterfaceManager");
            //    initializeInstanceDelegate ij=(initializeInstanceDelegate)Marshal.GetDelegateForFunctionPointer(ptrLoad, typeof(initializeInstanceDelegate));
            //    //initializeInstanceDelegate ii =(initializeInstanceDelegate)Marshal.GetDelegateForFunctionPointer(ptrII, typeof(initializeInstanceDelegate));
            //    bool ret = false;
            //    ret=ij();
            //}
            //catch(Exception ex) {
            //    System.Console.WriteLine(ex.Message);
            //}
            //finally
            //{
            //    // ライブラリを解放
            //    FreeLibrary(ptrLib);
            //}
        }

    }
}
