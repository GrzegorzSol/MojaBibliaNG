function przetworzTekst(idElementu)
{
	var div = document.getElementById(idElementu);
	if (!div) return;
		
	var tekst = div.innerText || div.textContent;
	var slowa = tekst.match(/[a-zA-Z0-9ąćęłńóśźżĄĆĘŁŃÓŚŹŻ]+/g);
	var nowyHTML = [];

	for (var i = 0; i < slowa.length; i++)
	{
		var slowo = slowa[i];
		var html = '<span class="slowo" id="s' + i + '" onclick="klik(\'' + slowo + '\', \'s' + i + '\')">' + slowo + '</span>';
		nowyHTML.push(html);
	}

	// Dodaj dodatkową spację po ostatnim słowie
	nowyHTML.push('&nbsp;');
	div.innerHTML = nowyHTML.join(' '); //??
}

function klik(slowo, id)
{
	var wszystkie = document.getElementsByTagName('span');
	for (var i = 0; i < wszystkie.length; i++)
	{
		if (wszystkie[i].className.indexOf('slowo') !== -1)
		{
			wszystkie[i].className = 'slowo';
		}
	}

	var klikniety = document.getElementById(id);
	klikniety.className += ' zaznaczone';

	window.location.href = "app://" + slowo;
}