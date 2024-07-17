package com.stt0504;

import com.stt0504.Entities.Color;
import lombok.Getter;
import lombok.Setter;
import lombok.experimental.Accessors;

import java.time.LocalDate;
import java.util.List;

@Getter
@Setter
@Accessors(chain = true)
public class CatDTO {
    private Long id;
    private String name;
    private String breed;
    private Color color;
    private Long ownerId;
    private List<Long> friendIds;
}
