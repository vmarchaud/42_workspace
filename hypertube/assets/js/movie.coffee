currentPage = 1

window.onload = ->
  populateList = (movies) ->
    if movies.err
      alert JSON.stringify(movies.err.msg)
    else if movies && movies.length > 0
      $.each movies, (key, val) ->
        if val.id
          $.ajax
            url: '/movie/partial/'+val.id
            success: (partialData) ->
              $('.video-list').append partialData
            error: (xhr, ajaxOpt, err) ->
              # console.log xhr + ajaxOpt + err

  getForm = ->
    {
      sortBy: $('#sortBy').val(),
      order: $('#order').val(),
      page: currentPage,
      yearFrom: $('#yearFrom').val(),
      yearTo: $('#yearTo').val(),
    }

  search = (searchText) ->
    try
      if searchText != ''
        url = '/movie/search/' + searchText + '/'
      else
        url = '/movie/popular'
      $.ajax
        url: url
        data: getForm()
        success: (movies) -> populateList movies
        error: (xhr, ajaxOpt, err) ->
          # console.log xhr + ajaxOpt + err
    catch error
      # console.log error

  $('.searchform').submit (e) ->
    currentPage = 1
    $('.video-list').html ''
    search $('.searchform .movieName').val()
    return false

  @nextPage = ->
    currentPage = currentPage + 1
    search $('.searchform .movieName').val()

  $(window).scroll _.throttle(->
    if $(window).scrollTop() + $(window).height() > $(document).height() - $(window).height()
      nextPage()
  , 3000)

  onUserInput = ->
    $('.video-list').html ''
    $('.searchform .movieName').submit()

  # $('.searchform .movieName').keyup _.throttle(onUserInput, 3000)
  $('.searchform').change onUserInput

  search('')
