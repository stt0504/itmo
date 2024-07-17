package com.stt0504;

import java.util.HashMap;
import java.util.Map;

public class ColorConverter {

    private final Map<Color, ColorDTO> colorMap = new HashMap<>();
    private final Map<ColorDTO, Color> colorDTOMap = new HashMap<>();

    public ColorConverter() {
        for (ColorDTO colorDTO : ColorDTO.values()) {
            colorMap.put(Color.valueOf(colorDTO.name()), colorDTO);
        }

        for (Map.Entry<Color, ColorDTO> entry: colorMap.entrySet()) {
            colorDTOMap.put(entry.getValue(), entry.getKey());
        }
    }

    public ColorDTO convertToDTO(Color color) {
        return colorMap.get(color);
    }

    public Color convertToEntity(ColorDTO colorDTO) {
        return colorDTOMap.get(colorDTO);
    }
}
