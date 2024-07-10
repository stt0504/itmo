using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services;

public class ComputerComponentFactory
{
    public ComputerComponentFactory(
        ComponentFactory<CPU> cpuFactory,
        ComponentFactory<CPUCoolingSystem> coolerFactory,
        ComponentFactory<HDD>? hddFactory,
        ComponentFactory<Motherboard> motherboardFactory,
        ComponentFactory<PowerSupplyUnit> powerSupplyUnitFactory,
        ComponentFactory<RAM> ramFactory,
        ComponentFactory<SSD>? ssdFactory,
        ComponentFactory<SystemCase> systemCaseFactory,
        ComponentFactory<VideoCard>? videoCardFactory,
        ComponentFactory<WiFiAdapter>? wiFiAdapterFactory)
    {
        CPUFactory = cpuFactory;
        CoolerFactory = coolerFactory;
        HDDFactory = hddFactory;
        MotherboardFactory = motherboardFactory;
        PowerSupplyUnitFactory = powerSupplyUnitFactory;
        RAMFactory = ramFactory;
        SSDFactory = ssdFactory;
        SystemCaseFactory = systemCaseFactory;
        VideoCardFactory = videoCardFactory;
        WiFiAdapterFactory = wiFiAdapterFactory;
    }

    public ComponentFactory<CPU> CPUFactory { get; private set; }
    public ComponentFactory<CPUCoolingSystem> CoolerFactory { get; private set; }
    public ComponentFactory<HDD>? HDDFactory { get; private set; }
    public ComponentFactory<Motherboard> MotherboardFactory { get; private set; }
    public ComponentFactory<PowerSupplyUnit> PowerSupplyUnitFactory { get; private set; }
    public ComponentFactory<RAM> RAMFactory { get; private set; }
    public ComponentFactory<SSD>? SSDFactory { get; private set; }
    public ComponentFactory<SystemCase> SystemCaseFactory { get; private set; }
    public ComponentFactory<VideoCard>? VideoCardFactory { get; private set; }
    public ComponentFactory<WiFiAdapter>? WiFiAdapterFactory { get; private set; }
}