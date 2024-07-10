using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services;

public class ComputerDirector
{
    private Computer.Builder _builder;

    private string? _cpu;
    private string? _cooler;
    private string? _hdd;
    private string? _motherboard;
    private string? _powerSupplyUnit;
    private string? _ram;
    private string? _ssd;
    private string? _systemCase;
    private string? _videoCard;
    private string? _wiFiAdapter;

    private ComputerComponentFactory _factory;

    public ComputerDirector(Computer.Builder builder, ComputerComponentFactory factory)
    {
        _builder = builder;
        _factory = factory;
    }

    public ComputerDirector SetMotherboardName(string motherboardName)
    {
        _motherboard = motherboardName;
        return this;
    }

    public ComputerDirector SetCPUName(string cpuName)
    {
        _cpu = cpuName;
        return this;
    }

    public ComputerDirector SetCoolerName(string cooler)
    {
        _cooler = cooler;
        return this;
    }

    public ComputerDirector SetRAMName(string ram)
    {
        _ram = ram;
        return this;
    }

    public ComputerDirector SetVideoCardName(string videoCard)
    {
        _videoCard = videoCard;
        return this;
    }

    public ComputerDirector SetSSDName(string ssd)
    {
        _ssd = ssd;
        return this;
    }

    public ComputerDirector SetSystemCaseName(string systemCase)
    {
        _systemCase = systemCase;
        return this;
    }

    public ComputerDirector SetPowerUnitName(string powerUnitName)
    {
        _powerSupplyUnit = powerUnitName;
        return this;
    }

    public ComputerDirector SetHDDName(string hddName)
    {
        _hdd = hddName;
        return this;
    }

    public ComputerDirector SetWifiAdapterName(string wifiAdapterName)
    {
        _wiFiAdapter = wifiAdapterName;
        return this;
    }

    public Computer Construct()
    {
        CPU? cpu = _factory.CPUFactory.Create(_cpu);
        CPUCoolingSystem? cooler = _factory.CoolerFactory.Create(_cooler);
        HDD? hdd = _factory.HDDFactory?.Create(_hdd);
        Motherboard? motherboard = _factory.MotherboardFactory.Create(_motherboard);
        PowerSupplyUnit? powerSupplyUnit = _factory.PowerSupplyUnitFactory.Create(_powerSupplyUnit);
        RAM? ram = _factory.RAMFactory.Create(_ram);
        SSD? ssd = _factory.SSDFactory?.Create(_ssd);
        SystemCase? systemCase = _factory.SystemCaseFactory.Create(_systemCase);
        VideoCard? videoCard = _factory.VideoCardFactory?.Create(_videoCard);
        WiFiAdapter? wiFiAdapter = _factory.WiFiAdapterFactory?.Create(_wiFiAdapter);

        if (cpu != null) _builder.SetCPU(cpu);
        if (cooler != null) _builder.SetCooler(cooler);
        if (hdd != null) _builder.SetHDD(hdd);
        if (motherboard != null) _builder.SetMotherboard(motherboard);
        if (powerSupplyUnit != null) _builder.SetPowerUnit(powerSupplyUnit);
        if (ram != null) _builder.SetRAM(ram);
        if (ssd != null) _builder.SetSSD(ssd);
        if (systemCase != null) _builder.SetSystemCase(systemCase);
        if (videoCard != null) _builder.SetVideoCard(videoCard);
        if (wiFiAdapter != null) _builder.SetWifiAdapter(wiFiAdapter);

        return _builder.Build();
    }
}