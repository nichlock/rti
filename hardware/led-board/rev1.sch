<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.2.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="16" fill="1" visible="no" active="no"/>
<layer number="3" name="Route3" color="17" fill="1" visible="no" active="no"/>
<layer number="4" name="Route4" color="18" fill="1" visible="no" active="no"/>
<layer number="5" name="Route5" color="19" fill="1" visible="no" active="no"/>
<layer number="6" name="Route6" color="25" fill="1" visible="no" active="no"/>
<layer number="7" name="Route7" color="26" fill="1" visible="no" active="no"/>
<layer number="8" name="Route8" color="27" fill="1" visible="no" active="no"/>
<layer number="9" name="Route9" color="28" fill="1" visible="no" active="no"/>
<layer number="10" name="Route10" color="29" fill="1" visible="no" active="no"/>
<layer number="11" name="Route11" color="30" fill="1" visible="no" active="no"/>
<layer number="12" name="Route12" color="20" fill="1" visible="no" active="no"/>
<layer number="13" name="Route13" color="21" fill="1" visible="no" active="no"/>
<layer number="14" name="Route14" color="22" fill="1" visible="no" active="no"/>
<layer number="15" name="Route15" color="23" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="SFH 4775S">
<packages>
<package name="4775S">
<rectangle x1="-1.4" y1="0" x2="1.4" y2="0.5" layer="29"/>
<rectangle x1="-0.8" y1="0.5" x2="0.8" y2="1.5" layer="29"/>
<rectangle x1="-0.3" y1="1.5" x2="0.3" y2="2.1" layer="29"/>
<rectangle x1="-0.6" y1="-0.9" x2="0.6" y2="-0.3" layer="29"/>
<rectangle x1="-0.3" y1="-1.4" x2="0.3" y2="-0.9" layer="29"/>
<smd name="ANODE" x="0" y="1" dx="1" dy="1.6" layer="1" rot="R90" stop="no" thermals="no"/>
<smd name="CATHODE" x="0" y="-0.6" dx="0.6" dy="1.2" layer="1" rot="R90" stop="no" thermals="no"/>
<text x="2.54" y="2.54" size="0.762" layer="21" rot="R270">&gt;NAME</text>
<wire x1="1" y1="1.65" x2="1" y2="-1.05" width="0.127" layer="21"/>
<wire x1="1" y1="-1.05" x2="-1" y2="-1.05" width="0.127" layer="21"/>
<wire x1="-1" y1="-1.05" x2="-1" y2="1.65" width="0.127" layer="21"/>
<wire x1="-1" y1="1.65" x2="1" y2="1.65" width="0.127" layer="21"/>
<wire x1="-0.9" y1="1.9" x2="0.9" y2="1.9" width="0.127" layer="21"/>
<smd name="ANODE1" x="0" y="1.8" dx="0.6" dy="0.6" layer="1" stop="no"/>
<smd name="CATHODE1" x="0" y="-1.15" dx="0.6" dy="0.5" layer="1" stop="no"/>
<smd name="ANODE2" x="0" y="0.25" dx="2.8" dy="0.5" layer="1" stop="no"/>
</package>
</packages>
<symbols>
<symbol name="LED">
<wire x1="5.08" y1="0" x2="12.7" y2="0" width="0.254" layer="94"/>
<text x="-7.62" y="-7.62" size="1.27" layer="94">IR LED 4775S</text>
<text x="-7.62" y="7.62" size="1.27" layer="94">&gt;NAME</text>
<pin name="ANODE" x="-12.7" y="0" visible="off" length="point"/>
<pin name="CATHODE" x="12.7" y="0" visible="off" length="point"/>
<wire x1="-5.08" y1="5.08" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-5.08" y2="0" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="-12.7" y1="0" x2="-5.08" y2="0" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="4775S">
<gates>
<gate name="G$1" symbol="LED" x="0" y="0"/>
</gates>
<devices>
<device name="" package="4775S">
<connects>
<connect gate="G$1" pin="ANODE" pad="ANODE ANODE1 ANODE2"/>
<connect gate="G$1" pin="CATHODE" pad="CATHODE CATHODE1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="1414Cathode">
<packages>
<package name="LED">
<smd name="THERM" x="0" y="0" dx="1.5" dy="3.5" layer="1" rot="R180" stop="no"/>
<smd name="CATHODE" x="1.4" y="0" dx="0.7" dy="3.5" layer="1" rot="R180" stop="no"/>
<smd name="ANODE" x="-1.4" y="0" dx="0.7" dy="3.5" layer="1" rot="R180" stop="no"/>
<wire x1="-1.65" y1="-1.65" x2="1.65" y2="-1.65" width="0.127" layer="21"/>
<wire x1="1.65" y1="-1.65" x2="1.65" y2="1.65" width="0.127" layer="21"/>
<wire x1="1.65" y1="1.65" x2="-1.65" y2="1.65" width="0.127" layer="21"/>
<wire x1="-1.65" y1="1.65" x2="-1.65" y2="-1.65" width="0.127" layer="21"/>
<rectangle x1="-1.6" y1="-1.6" x2="-1" y2="1.6" layer="29"/>
<rectangle x1="-0.75" y1="-1.6" x2="0.75" y2="1.6" layer="29"/>
<rectangle x1="1" y1="-1.6" x2="1.6" y2="1.6" layer="29"/>
<rectangle x1="0.75" y1="-0.4" x2="1" y2="0.4" layer="21"/>
<wire x1="-2" y1="1.6" x2="-2" y2="-1.6" width="0.127" layer="21"/>
<text x="-2" y="2" size="0.762" layer="21">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="LED">
<pin name="ANODE" x="-12.7" y="0" visible="off" length="point"/>
<pin name="CATHODE" x="12.7" y="0" visible="off" length="point" rot="R180"/>
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="0" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="-12.7" y1="0" x2="-5.08" y2="0" width="0.254" layer="94"/>
<wire x1="12.7" y1="0" x2="5.08" y2="0" width="0.254" layer="94"/>
<text x="-5.08" y="5.08" size="1.778" layer="94">&gt;NAME</text>
<text x="-12.7" y="-7.62" size="1.778" layer="94">UV LED SST-10-UV</text>
<pin name="THERM" x="-12.7" y="5.08" visible="off" direction="nc"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="SST-10-UV">
<gates>
<gate name="G$1" symbol="LED" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LED">
<connects>
<connect gate="G$1" pin="ANODE" pad="ANODE"/>
<connect gate="G$1" pin="CATHODE" pad="CATHODE"/>
<connect gate="G$1" pin="THERM" pad="THERM"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="1414Anode">
<packages>
<package name="LED">
<smd name="THERM" x="0" y="0" dx="1.5" dy="3.5" layer="1" rot="R180" stop="no"/>
<smd name="CATHODE" x="1.4" y="0" dx="0.7" dy="3.5" layer="1" rot="R180" stop="no"/>
<smd name="ANODE" x="-1.4" y="0" dx="0.7" dy="3.5" layer="1" rot="R180" stop="no"/>
<wire x1="-1.65" y1="-1.65" x2="1.65" y2="-1.65" width="0.127" layer="21"/>
<wire x1="1.65" y1="-1.65" x2="1.65" y2="1.65" width="0.127" layer="21"/>
<wire x1="1.65" y1="1.65" x2="-1.65" y2="1.65" width="0.127" layer="21"/>
<wire x1="-1.65" y1="1.65" x2="-1.65" y2="-1.65" width="0.127" layer="21"/>
<rectangle x1="-1.6" y1="-1.6" x2="-1" y2="1.6" layer="29"/>
<rectangle x1="-0.75" y1="-1.6" x2="0.75" y2="1.6" layer="29"/>
<rectangle x1="1" y1="-1.6" x2="1.6" y2="1.6" layer="29"/>
<rectangle x1="-1" y1="-0.4" x2="-0.75" y2="0.4" layer="21"/>
<wire x1="-2" y1="1.6" x2="-2" y2="-1.6" width="0.127" layer="21"/>
<text x="-1.778" y="2.159" size="0.762" layer="21">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="LED">
<pin name="ANODE" x="-12.7" y="0" visible="off" length="point"/>
<pin name="CATHODE" x="12.7" y="0" visible="off" length="point" rot="R180"/>
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="0" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="-12.7" y1="0" x2="-5.08" y2="0" width="0.254" layer="94"/>
<wire x1="12.7" y1="0" x2="5.08" y2="0" width="0.254" layer="94"/>
<text x="-5.08" y="5.08" size="1.778" layer="94">&gt;NAME</text>
<text x="-12.7" y="-7.62" size="1.778" layer="94">WHITE LED XLamp</text>
<pin name="THERM" x="-12.7" y="5.08" visible="off" direction="nc"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="XLAMPXPG2">
<gates>
<gate name="G$1" symbol="LED" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LED">
<connects>
<connect gate="G$1" pin="ANODE" pad="ANODE"/>
<connect gate="G$1" pin="CATHODE" pad="CATHODE"/>
<connect gate="G$1" pin="THERM" pad="THERM"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="wirepad" urn="urn:adsk.eagle:library:412">
<description>&lt;b&gt;Single Pads&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="SMD2,54-5,08" urn="urn:adsk.eagle:footprint:30823/1" library_version="1">
<description>&lt;b&gt;SMD PAD&lt;/b&gt;</description>
<smd name="1" x="0" y="0" dx="2.54" dy="5.08" layer="1"/>
<text x="0" y="0" size="0.0254" layer="27">&gt;VALUE</text>
<text x="-1.5" y="-2.5" size="1.27" layer="25" rot="R90">&gt;NAME</text>
</package>
</packages>
<packages3d>
<package3d name="SMD2,54-5,08" urn="urn:adsk.eagle:package:30841/1" type="box" library_version="1">
<description>SMD PAD</description>
<packageinstances>
<packageinstance name="SMD2,54-5,08"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="PAD" urn="urn:adsk.eagle:symbol:30808/1" library_version="1">
<wire x1="-1.016" y1="1.016" x2="1.016" y2="-1.016" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-1.016" x2="1.016" y2="1.016" width="0.254" layer="94"/>
<text x="-1.143" y="1.8542" size="1.778" layer="95">&gt;NAME</text>
<text x="-1.143" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="P" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="SMD5" urn="urn:adsk.eagle:component:30859/1" prefix="PAD" uservalue="yes" library_version="1">
<description>&lt;b&gt;SMD PAD&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SMD2,54-5,08">
<connects>
<connect gate="1" pin="P" pad="1"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:30841/1"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="IR" library="SFH 4775S" deviceset="4775S" device=""/>
<part name="UV" library="1414Cathode" deviceset="SST-10-UV" device=""/>
<part name="WHITE" library="1414Anode" deviceset="XLAMPXPG2" device=""/>
<part name="-IR" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD5" device="" package3d_urn="urn:adsk.eagle:package:30841/1"/>
<part name="-UV" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD5" device="" package3d_urn="urn:adsk.eagle:package:30841/1"/>
<part name="-W" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD5" device="" package3d_urn="urn:adsk.eagle:package:30841/1"/>
<part name="+" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD5" device="" package3d_urn="urn:adsk.eagle:package:30841/1"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="IR" gate="G$1" x="0" y="20.32">
<attribute name="NAME" x="-5.08" y="25.4" size="1.27" layer="94"/>
</instance>
<instance part="UV" gate="G$1" x="0" y="0">
<attribute name="NAME" x="-5.08" y="5.08" size="1.778" layer="94"/>
</instance>
<instance part="WHITE" gate="G$1" x="0" y="-20.32">
<attribute name="NAME" x="-5.08" y="-15.24" size="1.778" layer="94"/>
</instance>
<instance part="-IR" gate="1" x="35.56" y="20.32" rot="R180">
<attribute name="NAME" x="36.703" y="18.4658" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="36.703" y="23.622" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="-UV" gate="1" x="35.56" y="0" rot="R180">
<attribute name="NAME" x="36.703" y="-1.8542" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="36.703" y="3.302" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="-W" gate="1" x="35.56" y="-20.32" rot="R180">
<attribute name="NAME" x="36.703" y="-22.1742" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="36.703" y="-17.018" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="+" gate="1" x="-35.56" y="0">
<attribute name="NAME" x="-36.703" y="1.8542" size="1.778" layer="95"/>
<attribute name="VALUE" x="-36.703" y="-3.302" size="1.778" layer="96"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="ANODE" class="0">
<segment>
<wire x1="-17.78" y1="20.32" x2="-17.78" y2="0" width="0.1524" layer="91"/>
<pinref part="+" gate="1" pin="P"/>
<wire x1="-17.78" y1="0" x2="-17.78" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="0" x2="-17.78" y2="0" width="0.1524" layer="91"/>
<junction x="-17.78" y="0"/>
<pinref part="IR" gate="G$1" pin="ANODE"/>
<wire x1="-12.7" y1="20.32" x2="-17.78" y2="20.32" width="0.1524" layer="91"/>
<pinref part="UV" gate="G$1" pin="ANODE"/>
<wire x1="-12.7" y1="0" x2="-17.78" y2="0" width="0.1524" layer="91"/>
<pinref part="WHITE" gate="G$1" pin="ANODE"/>
<wire x1="-12.7" y1="-20.32" x2="-17.78" y2="-20.32" width="0.1524" layer="91"/>
<label x="-27.94" y="0" size="1.778" layer="95"/>
</segment>
</net>
<net name="CATH_IR" class="0">
<segment>
<pinref part="-IR" gate="1" pin="P"/>
<pinref part="IR" gate="G$1" pin="CATHODE"/>
<wire x1="33.02" y1="20.32" x2="12.7" y2="20.32" width="0.1524" layer="91"/>
<label x="17.78" y="20.32" size="1.778" layer="95"/>
</segment>
</net>
<net name="CATH_UV" class="0">
<segment>
<pinref part="-UV" gate="1" pin="P"/>
<pinref part="UV" gate="G$1" pin="CATHODE"/>
<wire x1="33.02" y1="0" x2="12.7" y2="0" width="0.1524" layer="91"/>
<label x="17.78" y="0" size="1.778" layer="95"/>
</segment>
</net>
<net name="CATH_W" class="0">
<segment>
<pinref part="WHITE" gate="G$1" pin="CATHODE"/>
<pinref part="-W" gate="1" pin="P"/>
<wire x1="12.7" y1="-20.32" x2="33.02" y2="-20.32" width="0.1524" layer="91"/>
<label x="17.78" y="-20.32" size="1.778" layer="95"/>
</segment>
</net>
<net name="THERM_UV" class="0">
<segment>
<pinref part="UV" gate="G$1" pin="THERM"/>
<wire x1="-12.7" y1="5.08" x2="-12.7" y2="10.16" width="0.1524" layer="91"/>
<label x="-12.7" y="10.16" size="1.778" layer="95"/>
</segment>
</net>
<net name="THERM_W" class="0">
<segment>
<pinref part="WHITE" gate="G$1" pin="THERM"/>
<wire x1="-12.7" y1="-15.24" x2="-12.7" y2="-10.16" width="0.1524" layer="91"/>
<label x="-12.7" y="-10.16" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
