using Lab05.Services;
using Spectre.Console;

namespace Lab05.Entities.Scenarios.UserOperations;

public class WithdrawMoneyScenario : IScenario
{
    private readonly IUserService _service;
    private IScenario? _nextScenario;

    public WithdrawMoneyScenario(IUserService service)
    {
        _service = service;
    }

    public string Name { get; } = "Withdraw money";

    public void SetNext(IScenario nextScenario)
    {
        _nextScenario = nextScenario;
    }

    public void Run()
    {
        AnsiConsole.Clear();

        int amount = AnsiConsole.Ask<int>("Enter amount: ");
        _service.Withdraw(amount);

        _nextScenario?.Run();
    }
}