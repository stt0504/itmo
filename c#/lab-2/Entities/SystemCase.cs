using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Models;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class SystemCase : IComponent<SystemCase>
{
    private SystemCase(string name, double maxVideoCardLength, double maxVideoCardWidth, Collection<FormFactor> supportedFormFactors, int width, int height)
    {
        Name = name;
        MaxVideoCardLength = maxVideoCardLength;
        MaxVideoCardWidth = maxVideoCardWidth;
        SupportedFormFactors = supportedFormFactors;
        Width = width;
        Height = height;
    }

    public string Name { get; private set; }
    public double MaxVideoCardLength { get; private set; }
    public double MaxVideoCardWidth { get; private set; }
    public Collection<FormFactor> SupportedFormFactors { get; private set; }
    public int Width { get; private set; }
    public int Height { get; private set; }

    public SystemCase Clone()
    {
        var clonedSystemCase = new SystemCase(
            Name,
            MaxVideoCardLength,
            MaxVideoCardWidth,
            SupportedFormFactors,
            Width,
            Height);

        return clonedSystemCase;
    }

    public class Builder : IBuilder<SystemCase>
    {
        private double _maxVideoCardLength;
        private double _maxVideoCardWidth;
        private Collection<FormFactor> _supportedFormFactors = new();
        private int _width;
        private int _height;
        private string? _name;
        private Collection<IComponentValidator<SystemCase>> _validators;

        public Builder(Collection<IComponentValidator<SystemCase>> validators)
        {
            _validators = validators;
        }

        public Builder SetMaxVideoCardLength(double maxVideoCardLength)
        {
            _maxVideoCardLength = maxVideoCardLength;
            return this;
        }

        public Builder SetMaxVideoCardWidth(double maxVideoCardWidth)
        {
            _maxVideoCardWidth = maxVideoCardWidth;
            return this;
        }

        public Builder AddSupportedFormFactor(FormFactor formFactor)
        {
            _supportedFormFactors.Add(formFactor);
            return this;
        }

        public Builder SetWidth(int width)
        {
            _width = width;
            return this;
        }

        public Builder SetHeight(int height)
        {
            _height = height;
            return this;
        }

        public Builder SetName(string name)
        {
            _name = name;
            return this;
        }

        public SystemCase Build()
        {
            if (_name is null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            var systemCase = new SystemCase(
                _name,
                _maxVideoCardLength,
                _maxVideoCardWidth,
                _supportedFormFactors,
                _width,
                _height);

            foreach (IComponentValidator<SystemCase> validator in _validators)
            {
                ResultBase validationResult = validator.Validate(systemCase);
                if (validationResult is not ValidComponent<SystemCase>)
                {
                    throw new ArgumentException(validationResult.Comment);
                }
            }

            return systemCase;
        }
    }
}