namespace _453503_Пратько
{
    internal class Program
    {
        static void Main(string[] args)
        {
            double num1, num2;

            Console.WriteLine("Введите первое число: ");
            num1 = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("Введите второе число: ");
            num2 = Convert.ToDouble(Console.ReadLine());

            double result = num1 / num2;

            Console.WriteLine("Частное от деления: " + result);
        }
    }
}
