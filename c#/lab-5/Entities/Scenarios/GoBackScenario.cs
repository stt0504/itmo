using Spectre.Console;

namespace Lab05.Entities.Scenarios;

public class GoBackScenario : IScenario
{
    private IScenario? _nextScenario;

    public string Name { get; } = "Go back";

    public void SetNext(IScenario nextScenario)
    {
        _nextScenario = nextScenario;
    }

    public void Run()
    {
        AnsiConsole.Clear();
        _nextScenario?.Run();
    }
}