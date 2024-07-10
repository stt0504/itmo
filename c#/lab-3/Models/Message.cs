namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public class Message
{
    private Message(string heading, string body, ImportanceLevel importanceLevel)
    {
        Heading = heading;
        Body = body;
        ImportanceLevel = importanceLevel;
    }

    public string Heading { get; private set; }
    public string Body { get; private set; }
    public ImportanceLevel ImportanceLevel { get; private set; }

    public class Builder
    {
        private string _heading = string.Empty;
        private string _body = string.Empty;
        private ImportanceLevel _importanceLevel = ImportanceLevel.Level1;

        public Builder SetHeading(string heading)
        {
            _heading = heading;
            return this;
        }

        public Builder SetBody(string body)
        {
            _body = body;
            return this;
        }

        public Builder SetImportanceLevel(ImportanceLevel importanceLevel)
        {
            _importanceLevel = importanceLevel;
            return this;
        }

        public Message Build()
        {
            return new Message(_heading, _body, _importanceLevel);
        }
    }
}