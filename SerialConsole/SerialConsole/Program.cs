using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;


namespace SerialConsole
{    
    class Program
    {        
        static public SerialPort com;
        static void Main(string[] args)
        {
            char[] buffer = new char[1];
            com = new SerialPort("COM3");
            com.BaudRate = 115200;
            com.Parity = Parity.None;
            com.StopBits = StopBits.One;
            com.Handshake = Handshake.None;
           // com.ReadTimeout = 1000;
            com.ReadBufferSize = 16;
            com.Open();
           /* while (true)
            {
                com.Write((string)Console.ReadLine());
                try
                {
                    Console.WriteLine((char)com.ReadByte());
                }
                catch (TimeoutException) {
                    Console.WriteLine("NULL");
                }
            }*/            
            while (true)
            {
                com.Write("R");
                waitForCom('A');
                string S = Console.ReadLine();
                if (S.Length < 9)
                    sendString(S);
                Console.Read();
            }
        }

        static void waitForCom(char c)
        {
            while(com.ReadByte() != c) ;
        }

        static void sendString(string s)
        {           
            for (int i = 0; i < s.Length; i++)
            {  
                com.Write("D" + (char)i + s[i]);
                waitForCom('A');
            }
            com.Write("S");
        }
    }
}
