namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public interface IDisplayDriver
{
    public void Clear();
    public void SetColor(Color color);
    public void PrintMessage(Message message);
}