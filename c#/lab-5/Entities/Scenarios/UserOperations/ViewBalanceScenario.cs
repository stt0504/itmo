using System.Globalization;
using Lab05.Services;
using Spectre.Console;

namespace Lab05.Entities.Scenarios.UserOperations;

public class ViewBalanceScenario : IScenario
{
    private readonly IUserService _service;
    private IScenario? _nextScenario;

    public ViewBalanceScenario(IUserService service)
    {
        _service = service;
    }

    public string Name { get; } = "View balance";

    public void SetNext(IScenario nextScenario)
    {
        _nextScenario = nextScenario;
    }

    public void Run()
    {
        AnsiConsole.Clear();

        int balance = _service.ViewBalance();

        AnsiConsole.Write("Balance: ");
        AnsiConsole.WriteLine(CultureInfo.InvariantCulture, balance);
        AnsiConsole.WriteLine("Press any key to continue...");
        Console.ReadKey(true);

        _nextScenario?.Run();
    }
}