#include "themestore.h"

ColorScheme ThemeStore::colorScheme(ColorSchemes name) {
    BaseColorScheme base;
    QPalette p;
    switch(name) {
        case COLORS_SYSTEM:
            base.folderview_topbar = p.window().color();
            base.widget = p.window().color();
            base.widget_border = p.window().color();
            base.folderview = p.base().color();
            base.text = p.text().color();
            base.icons = p.text().color();
            base.accent = p.highlight().color();
            base.scrollbar.setHsv(p.highlight().color().hue(),
                                  qBound(0, p.highlight().color().saturation() - 20, 240),
                                  qBound(0, p.highlight().color().value() - 35, 240));
            break;
        case COLORS_LIGHT: // v2, works with w10 titlebars
            base.accent = "#719ccd";
            base.background = "#1a1a1a";
            base.background_fullscreen = "#1a1a1a";
            base.folderview = "#f2f2f2";
            base.folderview_topbar = "#ffffff";
            base.icons = "#55585c";
            base.overlay = "#1a1a1a";
            base.overlay_text = "#d2d2d2";
            base.text = "#353535";
            base.scrollbar = "#aaaaaa";
            base.widget = "#ffffff";
            base.widget_border = "#c3c3c3";
            break;
        case COLORS_DARKBLUE:
            base.background = "#18191a";
            base.background_fullscreen = "#18191a";
            base.text = "#cdd2d7";
            base.icons = "#babec3";
            base.widget = "#232629";
            base.widget_border = "#26292d";
            base.accent = "#336ca5";
            base.folderview = "#232629";
            base.folderview_topbar = "#31363b";
            base.scrollbar = "#42484f";
            base.overlay_text = "#d2d2d2";
            base.overlay = "#1a1a1a";
            break;
        case COLORS_BLACK:
            base.background = "#000000";
            base.background_fullscreen = "#000000";
            base.text = "#b0b0b0";
            base.icons = "#999999";
            base.widget = "#080808";
            base.widget_border = "#181818";
            base.accent = "#3a3a3a";
            base.folderview = "#111111";
            base.folderview_topbar = "#111111";
            base.scrollbar = "#222222";
            base.overlay_text = "#666666";
            base.overlay = "#000000";
            break;
        case COLORS_DARK:
        case COLORS_DEFAULT:
            base.background = "#1a1a1a";
            base.background_fullscreen = "#1a1a1a";
            base.text = "#b4b4b4";
            base.icons = "#a4a4a4";
            base.widget = "#252525";
            base.widget_border = "#2c2c2c";
            base.accent = "#5a9147";
            base.folderview = "#242424";
            base.folderview_topbar = "#383838";
            base.scrollbar = "#5e5e5e";
            base.overlay_text = "#d2d2d2";
            base.overlay = "#1a1a1a";
            break;
    }
    return ColorScheme(base);
}

//---------------------------------------------------------------------

ColorScheme::ColorScheme() {
}

ColorScheme::ColorScheme(BaseColorScheme base) {
    setBaseColors(base);
}

void ColorScheme::setBaseColors(BaseColorScheme base) {
    background            = base.background;
    background_fullscreen = base.background_fullscreen;
    text                  = base.text;
    icons                 = base.icons;
    widget                = base.widget;
    widget_border         = base.widget_border;
    accent                = base.accent;
    folderview            = base.folderview;
    folderview_topbar     = base.folderview_topbar;
    overlay               = base.overlay;
    overlay_text          = base.overlay_text;
    scrollbar             = base.scrollbar;
    createColorVariants();
}

void ColorScheme::createColorVariants() {
    if(widget.valueF() <= 0.45f) { // dark theme
        // top bar buttons
        panel_button.setHsv(folderview_topbar.hue(), folderview_topbar.saturation(), qMin(folderview_topbar.value() + 20, 255));
        panel_button_hover.setHsv(folderview_topbar.hue(), folderview_topbar.saturation(), qMin(folderview_topbar.value() + 26, 255));
        panel_button_pressed.setHsv(folderview_topbar.hue(), folderview_topbar.saturation(), qMin(folderview_topbar.value() + 15, 255));
        folderview_hc.setHsv(folderview.hue(), folderview.saturation(), qMin(folderview.value() + 12, 255));
        folderview_hc2.setHsv(folderview.hue(), folderview.saturation(), qMin(folderview.value() + 28, 255));
        folderview_button_pressed = folderview_hc;
        folderview_button_hover = folderview_hc2;
        // regular buttons - from widget bg
        button.setHsv(widget.hue(), widget.saturation(), qMin(widget.value() + 21, 255));
        button_hover    = QColor(button.lighter(112));
        button_pressed  = QColor(button.darker(112));
        scrollbar_hover = scrollbar.lighter(120);
        // text
        text_hc = QColor(text.lighter(110));
        text_hc2 = QColor(text.lighter(118));
        text_lc = QColor(text.darker(115));
        text_lc2 = QColor(text.darker(160));
    } else { // light theme
        // top bar buttons
        panel_button.setHsv(folderview_topbar.hue(), folderview_topbar.saturation(), qMax(folderview_topbar.value() - 30, 0));
        panel_button_hover.setHsv(folderview_topbar.hue(), folderview_topbar.saturation(), qMax(folderview_topbar.value() - 45, 0));
        panel_button_pressed.setHsv(folderview_topbar.hue(), folderview_topbar.saturation(), qMax(folderview_topbar.value() - 55, 0));
        folderview_hc.setHsv(folderview.hue(), folderview.saturation(), qMax(folderview.value() - 25, 0));
        folderview_hc2.setHsv(folderview.hue(), folderview.saturation(), qMax(folderview.value() - 60, 0));
        folderview_button_pressed = folderview_hc2;
        folderview_button_hover = folderview_hc;
        // regular buttons - from widget bg
        button.setHsv(widget.hue(), widget.saturation(), qMax(widget.value() - 42, 0));
        button_hover    = QColor(button.darker(106));
        button_pressed  = QColor(button.darker(118));
        scrollbar_hover = scrollbar.darker(120);
        // text
        text_hc = QColor(text.darker(104));
        text_hc2 = QColor(text.darker(112));
        text_lc = QColor(text.lighter(130));
        text_lc2 = QColor(text.lighter(160));
    }
    // misc
    input_field_focus = QColor(accent);
}

