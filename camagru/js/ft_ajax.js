var ajax = {};

ajax.new = function () {
    return new XMLHttpRequest();
};

ajax.send = function (url, sucesscallback, errorCallback, method, data, asyncc) {
    var x = ajax.new();
	if (typeof asyncc === 'undefined')
		asyncc = true;
	console.log("Request " + method + " on " + url + " | async = " + asyncc);
    x.open(method, url, asyncc);
    x.onreadystatechange = function () {
        if (x.readyState == 4) {
			if (x.status < 300) {
				console.log("Response code " + x.status);
				sucesscallback(x.responseText)
			} else {
				console.log("Response " + x.responseText + " with code " + x.status);
				errorCallback(x);
			}

        }
    };
    if (method == 'POST') {
        x.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    }
    x.send(data);
};

ajax.get = function (url, data, callback, errorCallback, asyncc) {
    var query = [];
    for (var key in data) {
        query.push(encodeURIComponent(key) + '=' + encodeURIComponent(data[key]));
    }
    ajax.send(url + (query.length > 0 ? '?' + query.join('&') : ''), callback, errorCallback, 'GET', null, asyncc)
};

ajax.put = function (url, data, callback, errorCallback, asyncc) {
    var query = [];
    for (var key in data) {
        query.push(encodeURIComponent(key) + '=' + encodeURIComponent(data[key]));
    }
    ajax.send(url, callback, errorCallback, 'PUT', (query.length > 0 ? query.join('&') : ''), asyncc);
};

ajax.post = function (url, data, callback, errorCallback, asyncc) {
    var query = [];
    for (var key in data) {
        query.push(encodeURIComponent(key) + '=' + encodeURIComponent(data[key]));
    }
    ajax.send(url, callback, errorCallback, 'POST', query.join('&'), asyncc);
};
