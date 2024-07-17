package com.stt0504;

import java.util.List;
import java.util.stream.Collectors;

public class OwnerService {
    private final OwnerDAO ownerDAO;

    public OwnerService(OwnerDAO ownerDAO) {
        this.ownerDAO = ownerDAO;
    }

    public OwnerDTO addOwner(OwnerDTO owner) {
        if (owner.getName() == null || owner.getName().isEmpty()) {
            throw new IllegalArgumentException("Owner's name cannot be null");
        }
        return convert(ownerDAO.addOwner(convert(owner)));
    }

    public List<OwnerDTO> getOwners() {
        List<Owner> owners = ownerDAO.getAllOwners();
        return owners.stream()
                .map(this::convert)
                .collect(Collectors.toList());
    }

    public OwnerDTO getOwnerById(Long id) {

        return convert(ownerDAO.getOwnerById(id));
    }

    public Owner convert(OwnerDTO owner) {
        return new Owner().setName(owner.getName())
                .setBirthDate(owner.getBirthDate());
    }

    public OwnerDTO convert(Owner owner) {
        return new OwnerDTO().setId(owner.getId())
                .setName(owner.getName())
                .setBirthDate(owner.getBirthDate())
                .setCatIds(owner.getCats().stream()
                .map(Cat::getId)
                .collect(Collectors.toList()));
    }
}
