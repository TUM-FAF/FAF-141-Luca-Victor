var myApp = angular.module('CoolApp',[]);

myApp.controller('mainController', ['$scope', '$http', function($scope, $http) {
  $http({
    method: 'GET',
    headers: {
      'Accept': 'application/json'
    },
    url: '/preferences'
  }).then(function successCallback(response) {
    console.log("+++++++++++++++++++++")
    console.log(response);
    $scope.preferences = response.data;
  }, function errorCallback(response) {
    console.log("something is wrong");
  });

  $scope.addPreference = function() {
    if ($scope.preference.name != undefined && $scope.preference.food != undefined) {
      var new_preference = $scope.preference;
      $http({
        method: 'POST',
        url: '/preferences',
        headers: {
          'Accept': 'application/json'
        },
        data: new_preference
      }).then(function successCallback(response) {
        $scope.preferences.unshift(new_preference);
        console.log(response.data);
      }, function errorCallback(response) {
        console.log("something is wrong while posting");
      });
      console.log(new_preference);
    }
    $scope.preference = '';
  }

  
}]);
