BYTES = 8;
var bytesToInt = function(bytes) {
  var i = 0;
  for (var x = 0; x < bytes.length; x++) {
    i |= +(bytes[x] << (x * 8));
  }
  return i;
};
function decodeUplink(input) {
  var decoded = {};
  var bytes = input.bytes;
  if (bytes.length !== BYTES) {
    throw new Error('Lat/Long must have exactly 8 bytes');
  }
  decoded.latitute = bytesToInt(bytes.slice(0, BYTES / 2))/1e7;
  decoded.longitude = bytesToInt(bytes.slice(BYTES / 2, BYTES))/1e7;
return {
  data: decoded,
  warnings: [],
  errors: []
  }
}