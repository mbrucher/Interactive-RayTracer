<map version="freeplane 1.2.0">
<!--To view this file, download free mind mapping software Freeplane from http://freeplane.sourceforge.net -->
<node TEXT="Interactive Raytracer" ID="ID_1723255651" CREATED="1283093380553" MODIFIED="1372457115453"><hook NAME="MapStyle">
    <conditional_styles>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,1" LAST="false">
            <node_level_condition VALUE="1" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,2" LAST="false">
            <node_level_condition VALUE="2" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,3" LAST="false">
            <node_level_condition VALUE="3" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,4" LAST="false">
            <node_level_condition VALUE="4" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
    </conditional_styles>

<map_styles>
<stylenode LOCALIZED_TEXT="styles.root_node">
<stylenode LOCALIZED_TEXT="styles.predefined" POSITION="right">
<stylenode LOCALIZED_TEXT="default" MAX_WIDTH="600" COLOR="#000000" STYLE="as_parent">
<font NAME="SansSerif" SIZE="10" BOLD="false" ITALIC="false"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.details"/>
<stylenode LOCALIZED_TEXT="defaultstyle.note"/>
<stylenode LOCALIZED_TEXT="defaultstyle.floating">
<edge STYLE="hide_edge"/>
<cloud COLOR="#f0f0f0" SHAPE="ROUND_RECT"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.user-defined" POSITION="right">
<stylenode LOCALIZED_TEXT="styles.topic" COLOR="#18898b" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subtopic" COLOR="#cc3300" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subsubtopic" COLOR="#669900">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.important">
<icon BUILTIN="yes"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.AutomaticLayout" POSITION="right">
<stylenode LOCALIZED_TEXT="AutomaticLayout.level.root" COLOR="#000000">
<font SIZE="18"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,1" COLOR="#18898b">
<font SIZE="16"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,2" COLOR="#cc3300">
<font SIZE="14"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,3" COLOR="#669900">
<font SIZE="12"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,4" COLOR="#3333ff">
<font SIZE="10"/>
</stylenode>
</stylenode>
</stylenode>
</map_styles>
</hook>
<hook NAME="AutomaticEdgeColor" COUNTER="12"/>
<hook NAME="accessories/plugins/AutomaticLayout.properties" VALUE="ALL"/>
<node TEXT="Primitives" POSITION="right" ID="ID_777310371" CREATED="1363548219174" MODIFIED="1372457162604">
<edge COLOR="#ff0000"/>
<cloud COLOR="#f0f0f0" SHAPE="ARC"/>
<node TEXT="Sphere" ID="ID_1003872908" CREATED="1372457209889" MODIFIED="1372457215476">
<node TEXT="http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html" ID="ID_1141729979" CREATED="1372457331141" MODIFIED="1372457332553"/>
</node>
</node>
<node TEXT="Textures" POSITION="right" ID="ID_1819805371" CREATED="1363548224706" MODIFIED="1372457187014">
<edge COLOR="#0000ff"/>
<cloud COLOR="#f0f0f0" SHAPE="ARC"/>
</node>
<node TEXT="Optimization" POSITION="left" ID="ID_600828165" CREATED="1372457238337" MODIFIED="1372457268229">
<edge COLOR="#7c7c00"/>
<cloud COLOR="#f0f0f0" SHAPE="ARC"/>
<node TEXT="Vectorization" ID="ID_1675755996" CREATED="1372457269170" MODIFIED="1372457277501">
<node TEXT="Tree traversal" ID="ID_378179204" CREATED="1372457278184" MODIFIED="1372457288722"/>
<node TEXT="Primitive collision" ID="ID_554830143" CREATED="1372457289710" MODIFIED="1372457297402"/>
</node>
<node TEXT="Mail box" ID="ID_1019228067" CREATED="1372457304838" MODIFIED="1372457311874"/>
</node>
</node>
</map>
