.pragma library

function colorOpacity(color, opacity) {
    var hex_opacity = parseInt((opacity * 255),10).toString(16)
    var new_color = color
    if(color.length > 7) {
        new_color = "#" + hex_opacity + color.substring(3)
    } else {
        new_color = "#" + hex_opacity + color.substring(1)
    }
    return new_color
}
