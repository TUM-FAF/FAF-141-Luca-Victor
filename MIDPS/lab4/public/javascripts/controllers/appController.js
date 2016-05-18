var myApp = angular.module('CoolApp',[]);

myApp.controller('mainController', ['$scope', '$http', function($scope, $http) {
  $http({
    method: 'GET',
    headers: {
      'Accept': 'application/json'
    },
    url: '/preferences'
  }).then(function successCallback(response) {
    // this callback will be called asynchronously
    // when the response is available
    console.log("+++++++++++++++++++++")
    console.log(response);
    $scope.preferences = response.data;
  }, function errorCallback(response) {
    console.log("something is wrong");
    // called asynchronously if an error occurs
    // or server returns response with an error status.
  });

  $scope.addPreference = function() {
    if ($scope.preference.name != undefined && $scope.preference.fruct != undefined) {
      var new_preference = $scope.preference;
      $http.post('/preferences', new_preference);
      console.log(new_preference);
    }
    $scope.preference = '';
  }
}]);
