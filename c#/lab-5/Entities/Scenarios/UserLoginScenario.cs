using Lab05.Services;
using Spectre.Console;

namespace Lab05.Entities.Scenarios;

public class UserLoginScenario : IScenario
{
    private readonly IUserService _service;
    private IScenario? _nextScenario;

    public UserLoginScenario(IUserService service)
    {
        _service = service;
    }

    public string Name { get; } = "Login as user";

    public void SetNext(IScenario nextScenario)
    {
        _nextScenario = nextScenario;
    }

    public void Run()
    {
        AnsiConsole.Clear();

        int accountNumber = AnsiConsole.Ask<int>("Enter account number: ");
        int pin = AnsiConsole.Ask<int>("Enter PIN: ");

        _service.Login(accountNumber, pin);

        _nextScenario?.Run();
    }
}