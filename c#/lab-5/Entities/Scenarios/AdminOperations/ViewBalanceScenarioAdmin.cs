using System.Globalization;
using Lab05.Services;
using Spectre.Console;

namespace Lab05.Entities.Scenarios.AdminOperations;

public class ViewBalanceScenarioAdmin : IScenario
{
    private readonly IAdminService _service;
    private IScenario? _nextScenario;

    public ViewBalanceScenarioAdmin(IAdminService service)
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

        int accountNumber = AnsiConsole.Ask<int>("Enter account number: ");
        int balance = _service.ViewBalance(accountNumber);

        AnsiConsole.WriteLine(CultureInfo.InvariantCulture, $"Balance: {balance}");
        AnsiConsole.WriteLine("Press any key to continue...");
        Console.ReadKey(true);

        _nextScenario?.Run();
    }
}