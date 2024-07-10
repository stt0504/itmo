using Lab05.Services;
using Spectre.Console;

namespace Lab05.Entities.Scenarios;

public class AdminLoginScenario : IScenario
{
    private readonly IAdminService _service;
    private IScenario? _nextScenario;

    public AdminLoginScenario(IAdminService service)
    {
        _service = service;
    }

    public string Name { get; } = "Login as administrator";

    public void SetNext(IScenario nextScenario)
    {
        _nextScenario = nextScenario;
    }

    public void Run()
    {
        AnsiConsole.Clear();

        string password = AnsiConsole.Ask<string>("Enter system password: ");
        _service.Login(password);

        _nextScenario?.Run();
    }
}