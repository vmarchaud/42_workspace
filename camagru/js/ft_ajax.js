var ajax = {};

ajax.new = function () {
    return new XMLHttpRequest();
};

ajax.send = function (url, sucesscallback, errorCallback, method, data) {
    var x = ajax.new();
    x.open(method, url, true);
    x.onreadystatechange = function () {
        if (x.readyState == 4) {
            sucesscallback(x.responseText)
        } else {
			errorCallback(x);
		}
    };
    if (method == 'POST') {
        x.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    }
    x.send(data);
};

ajax.get = function (url, data, callback, errorCallback) {
    var query = [];
    for (var key in data) {
        query.push(encodeURIComponent(key) + '=' + encodeURIComponent(data[key]));
    }
    ajax.send(url + (query.length > 0 ? '?' + query.join('&') : ''), callback, errorCallback, 'GET', null)
};

ajax.post = function (url, data, callback, errorCallback) {
    var query = [];
    for (var key in data) {
        query.push(encodeURIComponent(key) + '=' + encodeURIComponent(data[key]));
    }
    ajax.send(url, callback, errorCallback, 'POST', query.join('&'))
};
