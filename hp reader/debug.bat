:: manifest
windres manifest.rc -O coff -o manifest.res
windres res.rc -O coff -o res.res
:: manifest tool
mt.exe -manifest b.res -outputresource:"hp reader.exe,#1"