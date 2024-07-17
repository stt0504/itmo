package com.stt0504;

import lombok.Getter;
import lombok.Setter;
import lombok.experimental.Accessors;

import java.time.LocalDate;
import java.util.List;

@Getter
@Setter
@Accessors(chain = true)
public class OwnerDTO {
    private Long id;
    private String name;
    private LocalDate birthDate;
    private List<Long> catIds;
}
