using System.Collections.ObjectModel;
using Spectre.Console;

namespace Lab05.Entities.Scenarios;

public class AuthorizationChoiceScenario : IScenario
{
    private readonly Collection<IScenario> _scenarios;

    public AuthorizationChoiceScenario(Collection<IScenario> scenarios)
    {
        _scenarios = scenarios;
    }

    public string Name { get; } = "Choice of authorization";

    public void Run()
    {
        AnsiConsole.Clear();

        SelectionPrompt<IScenario> selector = new SelectionPrompt<IScenario>()
            .Title("Select action: ")
            .AddChoices(_scenarios)
            .UseConverter(x => x.Name);
        IScenario scenario = AnsiConsole.Prompt(selector);

        scenario.Run();
    }
}