"""Generate the committed local theme catalog; no network or third-party theme imports."""
import colorsys
import json
from pathlib import Path

families = [
    ("slate-ice", "Slate & Ice", 210), ("graphite", "Graphite", 220),
    ("arctic", "Arctic", 195), ("ocean", "Ocean", 205), ("cobalt", "Cobalt", 225),
    ("indigo", "Indigo", 245), ("iris", "Iris", 260), ("lavender", "Lavender", 275),
    ("plum", "Plum", 290), ("orchid", "Orchid", 305), ("rose", "Rose", 330),
    ("cranberry", "Cranberry", 345), ("ruby", "Ruby", 355), ("coral", "Coral", 12),
    ("terracotta", "Terracotta", 20), ("copper", "Copper", 27), ("amber", "Amber", 38),
    ("sandstone", "Sandstone", 43), ("honey", "Honey", 48), ("olive", "Olive", 65),
    ("moss", "Moss", 85), ("fern", "Fern", 105), ("forest", "Forest", 130),
    ("emerald", "Emerald", 150), ("jade", "Jade", 165), ("lagoon", "Lagoon", 177),
    ("teal", "Teal", 185), ("glacier", "Glacier", 200), ("steel", "Steel", 215),
    ("storm", "Storm", 230), ("midnight", "Midnight", 240), ("lilac", "Lilac", 265),
    ("heather", "Heather", 285), ("mulberry", "Mulberry", 315), ("blush", "Blush", 340),
    ("clay", "Clay", 18), ("espresso", "Espresso", 30), ("parchment", "Parchment", 52),
    ("sage", "Sage", 115), ("monochrome", "Monochrome", 0),
]
def color(h, s, light):
    return "#" + "".join(f"{round(x*255):02X}" for x in colorsys.hls_to_rgb((h%360)/360, light, s))
def tokens(h, dark, neutral=False):
    saturation=0 if neutral else .20
    return dict(background=color(h,saturation,.075 if dark else .965),
                surface=color(h,saturation,.125 if dark else 1),
                text=color(h,saturation,.94 if dark else .14),
                primary=color(h,0 if neutral else .5,.76 if dark else .36),
                accent=color(h+25,0 if neutral else .48,.76 if dark else .72),
                border=color(h,saturation,.28 if dark else .87))
def enrich(t, dark):
    t["muted"]="#B5C0CC" if dark else "#526071"
    t["hover"]="#334253" if dark else "#E6EDF4"
    def luminance(hexcolor):
        channels=[int(hexcolor[i:i+2],16)/255 for i in (1,3,5)]
        linear=[v/12.92 if v<=.04045 else ((v+.055)/1.055)**2.4 for v in channels]
        return sum(v*w for v,w in zip(linear,(.2126,.7152,.0722)))
    primary_luminance=luminance(t["primary"])
    t["onPrimary"]="#000000" if (primary_luminance+.05)/.05 >= 1.05/(primary_luminance+.05) else "#FFFFFF"
    t["danger"]="#FFB4AB" if dark else "#9B2525"
    return t
catalog=[]
for identifier,name,hue in families:
    dark=tokens(hue,True,identifier in ("monochrome","graphite"))
    light=tokens(hue,False,identifier in ("monochrome","graphite"))
    if identifier=="slate-ice":
        palette=json.loads((Path(__file__).resolve().parents[1]/"assets/brand/palette.json").read_text())
        dark={key:palette["dark_"+key] for key in ("background","surface","text","primary","accent","border")}
        light={key:palette["light_"+key] for key in ("background","surface","text","primary","accent","border")}
    catalog.append(dict(id=identifier,name=name,dark=enrich(dark,True),light=enrich(light,False)))
target=Path(__file__).resolve().parents[1]/"assets/themes/catalog.json"
target.parent.mkdir(parents=True,exist_ok=True)
target.write_text(json.dumps(catalog,indent=2)+"\n")
print(f"Generated {len(catalog)} families, {len(catalog)*2} variants")
