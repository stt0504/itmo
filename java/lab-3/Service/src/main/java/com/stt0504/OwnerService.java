package com.stt0504;

import com.stt0504.Dao.OwnerDAO;
import com.stt0504.Entities.Cat;
import com.stt0504.Entities.Owner;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
public class OwnerService {
    private final OwnerDAO ownerDAO;

    @Autowired
    public OwnerService(OwnerDAO ownerDAO) {
        this.ownerDAO = ownerDAO;
    }

    public void addOwner(OwnerDTO owner) {
        if (owner.getName() == null || owner.getName().isEmpty()) {
            throw new IllegalArgumentException("Owner's name cannot be null");
        }
        ownerDAO.save(convert(owner));
    }

    public List<OwnerDTO> getOwners() {
        List<Owner> owners = ownerDAO.findAll();
        return owners.stream()
                .map(this::convert)
                .collect(Collectors.toList());
    }

    public OwnerDTO getOwnerById(Long id) {
        Optional<Owner> optionalOwner = ownerDAO.findById(id);
        if (optionalOwner.isPresent()) {
            return convert(optionalOwner.get());
        } else {
            throw new IllegalArgumentException("Owner with id " + id + " is not found");
        }
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
