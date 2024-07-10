using Lab05.Services;
using Spectre.Console;

namespace Lab05.Entities.Scenarios.UserOperations;

public class AddMoneyScenario : IScenario
{
    private readonly IUserService _service;
    private IScenario? _nextScenario;

    public AddMoneyScenario(IUserService service)
    {
        _service = service;
    }

    public string Name { get; } = "Add money";

    public void SetNext(IScenario nextScenario)
    {
        _nextScenario = nextScenario;
    }

    public void Run()
    {
        AnsiConsole.Clear();

        int amount = AnsiConsole.Ask<int>("Enter amount: ");
        _service.Deposit(amount);

        _nextScenario?.Run();
    }
}