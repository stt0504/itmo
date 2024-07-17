package com.stt0504;

import lombok.Getter;
import lombok.Setter;
import lombok.experimental.Accessors;

import jakarta.persistence.*;
import java.time.LocalDate;
import java.util.List;

@Getter
@Setter
@Entity
@Accessors(chain = true)
@Table(name = "owners")
public class Owner {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "owner_id")
    private Long id;

    @Column(name = "name")
    private String name;

    @Column(name = "birth_date")
    private LocalDate birthDate;

    @OneToMany(mappedBy = "owner", fetch = FetchType.EAGER)
    private List<Cat> cats;
}
