using System.Collections.ObjectModel;
using System.Globalization;
using Lab05.Models;
using Lab05.Services;
using Spectre.Console;

namespace Lab05.Entities.Scenarios.AdminOperations;

public class ViewHistoryScenarioAdmin : IScenario
{
    private readonly IAdminService _service;
    private IScenario? _nextScenario;

    public ViewHistoryScenarioAdmin(IAdminService service)
    {
        _service = service;
    }

    public string Name { get; } = "View history";

    public void SetNext(IScenario nextScenario)
    {
        _nextScenario = nextScenario;
    }

    public void Run()
    {
        AnsiConsole.Clear();

        int accountNumber = AnsiConsole.Ask<int>("Enter account number: ");
        Collection<Operation> operations = _service.ViewHistory(accountNumber);

        foreach (Operation operation in operations)
        {
            AnsiConsole.Write(CultureInfo.InvariantCulture, $"Amount: {operation.Amount}; ");
            AnsiConsole.Write(CultureInfo.InvariantCulture, $"Operation type: {operation.OperationType}; ");
            AnsiConsole.Write(CultureInfo.InvariantCulture, $"Date: {operation.Date}; ");
            AnsiConsole.WriteLine(CultureInfo.InvariantCulture, $"Time: {operation.Time}");
        }

        AnsiConsole.WriteLine("Press any key to continue...");
        Console.ReadKey(true);

        _nextScenario?.Run();
    }
}