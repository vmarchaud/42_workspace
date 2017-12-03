const http = require('http')
const url = require('url')

function getMatches(string, regex, index) {
  index || (index = 1); // default to the first capturing group
  var matches = [];
  var match;
  while (match = regex.exec(string)) {
    matches.push(match[index]);
  }
  return matches;
}

const get = endpoint => {
  http.get(url.parse(endpoint), (res) => {
    res.setEncoding('utf8');
    let rawData = '';
    res.on('data', (chunk) => { rawData += chunk; });
    res.on('end', () => {
      console.log(rawData)
      if (rawData.indexOf('README') > -1)
        return get(endpoint + '/README')
      if (endpoint.indexOf('README') > -1)
        return console.log(rawData)
      let urls = getMatches(rawData, /href="(.*)\/">/g)
      urls.forEach(url => {
        if (url === '..') return
        return get(`${endpoint}/${url}`)
      })
    });
  })
}
get('http://10.12.1.139/.hidden/eipmnwhetmpbhiuesykfhxmyhr/gubyklkxvljikilfdqyajypgpt/gtmgedazcchqobjyuufjkxmmam')
