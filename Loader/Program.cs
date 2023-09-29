using Reloaded.Injector;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Loader
{
    internal class Program
    {
        /*
       * Autor: ZRD
       * 29.09.2023
       * Prosty injector do injectowania naszego dll, nie ma co wsumie tutaj dodawac komentarzy bo i tak osoba
       * ktora to przeglada raczej jest w miare zaawansowana aby zrozumiec kod bez komentarzy na dodatek jest to dosc krotki kod
       */
        static void Main(string[] args)
        {
            Console.Title = "Injector";
            Console.WriteLine(Process.GetProcessesByName("PJ2")[0]);
            var injector = new Injector(Process.GetProcessesByName("PJ2")[0]);
            injector.Inject("./SJ2Experiments.dll");

        }
    }
}
