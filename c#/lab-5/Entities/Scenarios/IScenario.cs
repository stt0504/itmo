namespace Lab05.Entities.Scenarios;

public interface IScenario
{
    string Name { get; }
    void Run();
}