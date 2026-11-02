<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
  <xsl:template match="/">
    <HTML>
      <BODY>
        <TABLE style="font:8pt MS Sans Serif" border="1" CELLSPACING="0" CELLPADDING="1" BGCOLOR="#FFFFFF">
          <THEAD style="font:bold; background-color:#C0C0C0">
            <TR valign="top">
              <xsl:for-each select="/GRID/COLUMNS/COLUMN">
                <TD align="left">
                  <xsl:attribute name="width"><xsl:value-of select="@Width"/></xsl:attribute>
                  <xsl:value-of select="@Caption"/>
                </TD>
              </xsl:for-each>
            </TR>
          </THEAD>
          <xsl:for-each select="GRID/ROWS/ROW">
          <TR valign="top">
            <TD align="left">
              <xsl:value-of select="@LibRef"/>
              <xsl:if test="@LibRef[.='']">&#160;</xsl:if>
            </TD>
            <TD align="left">
              <xsl:value-of select="@Footprint"/>
              <xsl:if test="@Footprint[.='']">&#160;</xsl:if>
            </TD>
            <TD align="left">
              <xsl:value-of select="@Description"/>
              <xsl:if test="@Description[.='']">&#160;</xsl:if>
            </TD>
            <TD align="left">
              <xsl:value-of select="@_Checked_PCB"/>
              <xsl:if test="@_Checked_PCB[.='']">&#160;</xsl:if>
            </TD>
            <TD align="left">
              <xsl:value-of select="@_Checked_SCH"/>
              <xsl:if test="@_Checked_SCH[.='']">&#160;</xsl:if>
            </TD>
            <TD align="left">
              <xsl:value-of select="@_Creator"/>
              <xsl:if test="@_Creator[.='']">&#160;</xsl:if>
            </TD>
            <TD align="left">
              <xsl:value-of select="@Library_Name"/>
              <xsl:if test="@Library_Name[.='']">&#160;</xsl:if>
            </TD>
          </TR>
          </xsl:for-each>
        </TABLE>
      </BODY>
    </HTML>
  </xsl:template>
</xsl:stylesheet>
